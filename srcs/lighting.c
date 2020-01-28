/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:15:25 by hhamdaou          #+#    #+#             */
/*   Updated: 2020/01/28 15:15:26 by hhamdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect ft_ambient()
{
    t_vect ambient;
    double ambient_str;

    ambient_str = 0.2;
    ambient.x = ambient_str;
    ambient.y = ambient_str;
    ambient.z = ambient_str;
    return (ambient);
}

t_vect ft_diffuse(t_light light, t_intersection inter)
{
    t_vect diffuse;

    diffuse.x = fmax(0, vector_scalar(inter.normal, light.dir)) * light.intensity;
    diffuse.y = fmax(0, vector_scalar(inter.normal, light.dir)) * light.intensity;
    diffuse.z = fmax(0, vector_scalar(inter.normal, light.dir)) * light.intensity;
    return (diffuse);
}

t_vect ft_specular(t_rtv1 r, t_light light, t_intersection inter)
{
    t_vect specular;
    t_vect view;
    double spec_str = 0.5;
    double str;
    t_vect R;

    view = vector_sub(r.cam.pos, inter.p_inter);
    vector_normalize(&view);
    light.dir = vector_multi(light.dir, -1);
    R = vector_sub(light.dir, vector_multi(inter.normal, 2 * vector_scalar(inter.normal, light.dir)));
    str = pow(fmax(vector_scalar(view, R), 0.), 250);
    specular.x = str * spec_str;
    specular.y = str * spec_str;
    specular.z = str * spec_str;
    return (specular);
}

t_lighting pixel_lighting(t_rtv1 r, t_intersection inter)
{
    t_lighting res;
    t_light *head;

    head = r.light;
    res.ambient = (t_vect){0, 0, 0};
    res.diffuse = (t_vect){0, 0, 0};
    res.specular = (t_vect){0, 0, 0};
    while (head)
    {
        head->dir = vector_sub(head->origin, inter.p_inter);
        vector_normalize(&head->dir);
        res.ambient = vector_sum(res.ambient, ft_ambient());
        res.diffuse = vector_sum(res.diffuse, ft_diffuse(*head, inter));
        res.specular = vector_sum(res.specular, ft_specular(r, *head, inter));
        head = head->next;
    }

    return (res);
}

int shadow_light(t_rtv1 r, t_intersection intersect)
{
    t_intersection *sh_inter;
    double fact;
    t_ray ray;
    t_light *head;
    int count;

    sh_inter = (t_intersection *)malloc(sizeof(t_intersection));
    fact = 0.5;
    count = 0;
    head = r.light;
    while (head)
    {
        head->dir = vector_sub(head->origin, intersect.p_inter);
        vector_normalize(&head->dir);
        vector_generate(&ray.origin, intersect.p_inter.x + (fact * intersect.normal.x), intersect.p_inter.y + (fact * intersect.normal.y), intersect.p_inter.z + (fact * intersect.normal.z));
        ray.dir = vector_sub(head->origin, ray.origin);
        vector_normalize(&ray.dir);
        intersection(ray, r.shape, sh_inter);
        sh_inter->normal = vector_sub(intersect.p_inter, sh_inter->p_inter);
        if (sh_inter->inter && head->intensity)
            count++;
        head = head->next;
        //printf("c = %i\n", count);
    }
    return (count);
}