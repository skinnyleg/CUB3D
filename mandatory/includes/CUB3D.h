/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CUB3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:18:31 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 23:09:12 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FOV 60
# define WIN_HEIGHT 800
# define WIN_WIDTH 1500
# define STRIP_WIDTH 1
# define TILE_SIZE 64

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>
# include <stdbool.h>
# include "../../libft/includes/libft.h"
# define BUFFER_SIZE 1

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_win;
	void	*image;
	char	*get_addr;
	int		sl;
	int		bpp;
	int		ed;
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
	double	x;
	double	y;
	double	pos_tilex;
	double	pos_tiley;
	int		vel;
	int		rld;
	int		rla;
	int		udd;
	double	rotateangle;
	double	rotatespeed;
	int		tile_width;
	int		tile_height;
}	t_player;

typedef struct s_rays
{
	bool	up;
	bool	right;
	bool	verthit;
	double	distance_vertic;
	double	distance_horiz;
	double	dist_const;
	double	horzx;
	double	horzy;
	double	vertx;
	double	verty;
	double	xnext;
	double	ynext;
	double	xstep;
	double	ystep;
	double	rad;
}	t_rays;

typedef struct s_textures
{
	int		**texture;
	void	*teximg[4];
	int		texelcolor;
	int		offsetx;
	int		offsety;
}	t_textures;

typedef struct s_global
{
	int			fd;
	int			a;
	int			l;
	int			num_rays;
	int			color_ceiling;
	int			color_floor;
	double		scale;
	double		wallheight;
	t_textures	*textures;
	t_paraup	*up;
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
	t_rays		*rays;
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
void		render_minimap(t_global *all);
void		destroy_rays(t_global *all);
int			iswall_ray(t_global *all, double x, double y);
int			keypress(int keycode, t_global *all);
int			keyrelease(int keycode, t_global *all);
int			ft_close(t_global *all);
int			move_player(t_global *all);
int			raycaster(t_global *all);
void		ft_normalize_angle(double *angle);
void		cast_render(t_global *all, t_rays *ray);
void		render3dwalls(t_global *all);
void		pixel_put(t_mlx *mlx, int x, int y, int color);
void		background_render(t_global *all);
void		render_block(t_global *all, int i, int j, int color);
void		render_rays(t_global *all, t_rays ray, double x, double y);
void		ft_direction_player(t_global *all, char p);
void		destroy_textures(t_global *all);
int			set_textures(t_global *all);
int			index_textures(t_global *all, int i);
void		render_direct(t_global *all, int size, double x, double y);
void		free_maparr(t_global *all);
double		distance_calcul(t_global *all, t_rays ray);
int			map_size(char **map);

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
