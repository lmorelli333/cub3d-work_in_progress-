/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:53:41 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/20 19:26:09 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(char *str);
char	*ft_strjoin_gnl(char *res, char *temp);
char	*ft_write_line(char *res);
char	*ft_new_res(char *res);
char	*ft_read_res(int fd, char *res);
#endif
