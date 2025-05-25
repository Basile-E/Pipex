/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_occurrences.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baecoliv <baecoliv@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:18:18 by baecoliv          #+#    #+#             */
/*   Updated: 2022/03/09 16:18:51 by baecoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_occurrences(char *str, char c)
{
	int	occurrences;
	int	i;

	i = 0;
	occurrences = 0;
	while (str[i])
	{
		if (str[i] == c)
			occurrences++;
		i++;
	}
	return (occurrences);
}
