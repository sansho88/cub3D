/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavaud <alavaud@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:17:45 by alavaud           #+#    #+#             */
/*   Updated: 2022/11/24 14:27:03 by alavaud          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_in_box(t_scissor *scissor, int x, int y)
{
	return (x >= scissor->x && y >= scissor->y
		&& x < (scissor->x + scissor->width)
		&& (y < (scissor->y + scissor->height)));
}

static void	line_putpixel(t_painter *painter, t_line_ctx *ctx)
{
	optimized_pixelput(painter->surf, ctx->x1, ctx->y1, painter->colpen);
	optimized_pixelput(painter->surf,
		ctx->x1 + ctx->sx, ctx->y1, painter->colpen);
	optimized_pixelput(painter->surf,
		ctx->x1, ctx->y1 + ctx->sy, painter->colpen);
}

void	draw_line(t_painter *painter, t_line_ctx *ctx)
{
	int	e2;

	while (1)
	{
		if (is_in_box(&painter->scissor, ctx->x1, ctx->y1))
			line_putpixel(painter, ctx);
		if (ctx->x1 == ctx->x2 && ctx->y1 == ctx->y2)
			break ;
		e2 = 2 * ctx->err;
		if (e2 >= ctx->dy)
		{
			ctx->err += ctx->dy;
			ctx->x1 += ctx->sx;
		}
		if (e2 <= ctx->dx)
		{
			ctx->err += ctx->dx;
			ctx->y1 += ctx->sy;
		}
	}
}

void	line_to(t_painter *painter, int x, int y)
{
	t_line_ctx	ctx;
	int			from[2];
	int			to[2];

	transform_point(painter, painter->xpen, painter->ypen, from);
	transform_point(painter, x, y, to);
	ctx.x1 = from[X];
	ctx.y1 = from[Y];
	ctx.x2 = to[X];
	ctx.y2 = to[Y];
	ctx.dx = abs(to[X] - from[X]);
	ctx.sx = -1;
	if (from[X] < to[X])
		ctx.sx = 1;
	ctx.dy = -abs(to[Y] - from[Y]);
	ctx.sy = -1;
	if (from[Y] < to[Y])
		ctx.sy = 1;
	ctx.err = ctx.dx + ctx.dy;
	draw_line(painter, &ctx);
	painter->xpen = x;
	painter->ypen = y;
}

void	move_to(t_painter *painter, int x, int y)
{
	painter->xpen = x;
	painter->ypen = y;
}
