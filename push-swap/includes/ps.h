/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 02:50:45 by yhetman           #+#    #+#             */
/*   Updated: 2019/10/19 17:58:38 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H

# include "../libft/includes/libft.h"

char	*sort_list(t_ilst	**first, int i);
int		run_throught_first(t_ilst **first, t_ilst *last, char **str);
void	run_throught_second(t_ilst **second, t_ilst *last, char **str);

#endif
