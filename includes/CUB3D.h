/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:18:31 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/22 21:03:18 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE_SIZE 4
# define WIN_HEIGHT 800
# define WIN_WIDTH 1500
# define MINI_HEIGHT 500
# define MINI_WIDTH 500

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
// # include "/usr/X11/include/mlx.h"
# include "../libft/includes/libft.h"
# define BUFFER_SIZE 1

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*image;
	char	*get_addr;
	int		size_line;
	int		bits_per_pixel;
	int		endian;
}	t_mlx;

typedef struct s_paraup
{
	char			*dir;
	char			*value;
	int				repate;
	struct s_paraup	*next;
}	t_paraup;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
	int		vel;
	int		rld;
	int		udd;
	double	rotateangle;
	double	rotatespeed;
}	t_player;

typedef struct s_global
{
	int			fd;
	int			a;
	int			l;
	t_paraup	*up;
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
}	t_global;

char		*ft_strjoin_free(char *s1,	char *s2);
int			parse_lower(char **av, t_global *all);
char		*get_next_line(int fd);
char		*gnl(int fd);
void		free_2d(char **map, int size);
int			change_line(t_global *all, char **line);
int			line_valid(char *line);
void		free_map(t_map *map);
void		free_2d(char **map, int size);
int			fill(char **av, t_global *all);
void		init_height(int fd, t_global *all);
int			fill_map(t_global *all, char **av);
void		player_count(char c, int *count);
int			check_cas(char c);
int			vertical_wall(t_map *map);
int			horizantal_wall(t_map *map);
int			check_contents(t_map *map);
int			check_extension(char *str, char *extension);
void		mlx_render(t_global *all);
int			render_minimap(t_global *all);

//created by med-doba
void		ft_free_lst_paraup(t_paraup **head);
int			ft_rtn_gnl(char *rtn_gnl, t_global *all);
int			check_double(t_paraup *up);
int			ft_check_ptr_0(char *ptr0);
char		*ft_strtrim_free(char const *s1, char const *set);
int			parse_upper(char	**av, t_global *all);
int			ft_handle_line(char	**ptr, t_global *up);
void		ft_lstadd_back_paraup(t_paraup **lst, t_paraup *new);
int			ft_lstsize_paraup(t_paraup *lst);
t_paraup	*ft_lstnew_paraup(char *name, char *value, int repate);
void		ft_free_2d(char **ptr);
int			ft_handle_c_f(char *ptr);
void		destroy_all(t_global *all);
#endif
