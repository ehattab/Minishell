/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehattab <ehattab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:56:01 by ehattab           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:02 by ehattab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*nelem;

	if (!lst || !f)
		return (NULL);
	nlst = NULL;
	while (lst != NULL)
	{
		nelem = ft_lstnew(f(lst->content));
		if (!nelem)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, nelem);
		lst = lst->next;
	}
	return (nlst);
}
