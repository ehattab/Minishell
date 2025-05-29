/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:25:17 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:40:52 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst == NULL)
		new->next = NULL;
	else
		new->next = *lst;
	*lst = new;
}
