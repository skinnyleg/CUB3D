/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:18:31 by hmoubal           #+#    #+#             */
/*   Updated: 2022/09/18 10:39:00 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
// # include <mlx.h>
# include "/usr/X11/include/mlx.h"
# include "../libft/includes/libft.h"
# define BUFFER_SIZE 1

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	char	**map;
}	t_mlx;

typedef struct s_paraup
{
	char	*dir;
	char	*value;
	int		repate;
	struct s_paraup	*next;
}	t_paraup;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_global
{
	int			fd;
	t_paraup	*up;
	t_map		*map;
}	t_global;

char	*ft_strjoin_free(char const *s1,	char const *s2);
//gnl
char	*get_next_line(int fd);
//created by med-doba
char		*ft_strtrim_free(char const *s1, char const *set);
int			parse_upper(char	**av, t_global *all);
int			ft_handle_line(char	**ptr, t_global *up);
void		ft_lstadd_back_paraup(t_paraup **lst, t_paraup *new);
t_paraup	*ft_lstnew_paraup(char *name, char *value, int repate);
void		ft_free_2d(char **ptr);
int			ft_handle_c_f(char *ptr);
#endif
