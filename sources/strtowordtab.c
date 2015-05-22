/*
** strtowordtab.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Tue Jan 20 00:26:54 2015 arnaud boulay
** Last update Fri May 22 18:13:09 2015 Sebastien BOULOC
*/

#include <stdlib.h>
#include "my.h"

int		count_words(char *str, char *sep)
{
  int		words;
  int		i;

  i = -1;
  words = 0;
  while (str[++i] != '\0')
    if ((is_cinside(sep, str[i]) == 0 && str[i] != '\t') &&
	(is_cinside(sep, str[i + 1]) == 1 ||
	 str[i + 1] == '\t' || str[i + 1] == '\0'))
      ++words;
  return (words);
}

int		my_wordlen(char *str, int *i, char *sep)
{
  int		j;

  j = 0;
  while (str[++(*i)] != '\0')
    if (is_cinside(sep, str[*i]) == 0 && str[*i] != '\t')
      {
	++j;
	if (is_cinside(sep, str[*i + 1]) == 1 ||
	    str[*i + 1] == '\t' || str[*i + 1] == '\0')
	  return (j);
      }
  return (-1);
}

char		*my_wordcpy(char *tab, char *str, int *i, char *sep)
{
  int		j;

  j = -1;
  while (str[++(*i)] != '\0')
    if (is_cinside(sep, str[*i]) == 0 && str[*i] != '\t')
      {
	tab[++j] = str[*i];
	if (is_cinside(sep, str[*i + 1]) == 1 ||
	    str[*i + 1] == '\t' || str[*i + 1] == '\0')
	  {
	    tab[++j] = '\0';
	    return (tab);
	  }
      }
  return (NULL);
}

char		**my_strtowordtab(char *str, char *sep)
{
  char		**tab;
  int		words;
  int		i;
  int		j;
  int		k;

  i = -1;
  j = -1;
  k = -1;
  if (str == NULL || sep == NULL)
    return (NULL);
  words = count_words(str, sep);
  if ((tab = malloc(sizeof(char *) * (words + 1))) == NULL)
    return (NULL);
  while (++i < words)
    {
      if ((tab[i] = malloc(sizeof(char) * (my_wordlen(str, &j, sep) + 1)))
	  == NULL)
	return (NULL);
      tab[i] = my_wordcpy(tab[i], str, &k, sep);
    }
  tab[i] = NULL;
  return (tab);
}

void		free_tab(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i] != NULL)
    free(tab[i]);
  free(tab[i]);
  free(tab);
}
