/*
** clear_screen.c for shell_get_line in /home/cassin_f/B2/B2-Systeme_Unix/42sh_cassin/functions
** 
** Made by François CASSIN
** Login   <cassin_f@epitech.net>
** 
** Started on  Mon May 18 14:26:27 2015 François CASSIN
** Last update Wed May 20 11:22:08 2015 François CASSIN
*/

#include "my_get_line.h"

void		decale_bytes_left(t_line *line, int offset)
{
  int		nb_bytes;

  if ((nb_bytes = analyze_char(line->buffer[offset - 1])) == 0)
    --line->cursor_offset;
  else
    {
      while (offset != 0 && analyze_char(line->buffer[offset - 1]) == 1)
	{
	  --line->cursor_offset;
	  --offset;
	}
      if (offset != 0)
	--line->cursor_offset;
    }

}

void		backward(t_params *params, t_line *line)
{
  if (line->cursor_offset > 0)
    {
      if (((line->cursor_begin + line->cursor_position - 1) %
	   params->caps->column + 1) == 1)
	{
	  xtputs_param(params->caps->UP_str, 1, my_putint, 1);
	  xtputs_param(params->caps->RIGHT_str, 1, my_putint,
		       params->caps->column - 1);
	}
      else
	xtputs(params->caps->left_str, 1, my_putint);
      decale_bytes_left(line, line->cursor_offset);
      --line->cursor_position;
    }
}
