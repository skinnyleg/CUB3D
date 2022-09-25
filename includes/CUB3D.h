/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:18:31 by hmoubal           #+#    #+#             */
/*   Updated: 2022/09/25 20:19:29 by med-doba         ###   ########.fr       */
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
	t_mlx		*mlx;
}	t_global;

char	*ft_strjoin_free(char const *s1,	char const *s2);
int		parse_map_walls(char **av, t_global *all);
char	*get_next_line(int fd);
//created by med-doba
int			check_double(t_paraup *up);
int 		ft_check_ptr_0(char *ptr0);
char		*ft_strtrim_free(char const *s1, char const *set);
int			parse_upper(char	**av, t_global *all);
int			ft_handle_line(char	**ptr, t_global *up);
void		ft_lstadd_back_paraup(t_paraup **lst, t_paraup *new);
int			ft_lstsize_paraup(t_paraup *lst);
t_paraup	*ft_lstnew_paraup(char *name, char *value, int repate);
void		ft_free_2d(char **ptr);
int			ft_handle_c_f(char *ptr);
#endif
