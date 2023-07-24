#include "readline.h"

/*------------- proto ---------------*/

/* ================================= */

char	*rd_cat_line(char *line, int pos, char c)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	len = rd_strlen(line);
	if (pos > len)
		pos = len;
	newline = malloc(sizeof(char) * (len + 2));
	if (!newline)
		return (NULL);
	for (; line && i < pos; i++)
		newline[i] = line[i];
	newline[i++] = c;
	for (; line && line[i - 1]; i++)
		newline[i] = line[i - 1];
	newline[i] = 0;
	free(line);
	return (newline);
}

char	*rd_remove_one(char *line, int pos)
{
	int		i;
	int		len;
	char	*newline;

	i = 0;
	if (pos == 0)
		return (line);
	len = rd_strlen(line);
	if (pos > len)
		pos = len;
	newline = malloc(sizeof(char) * (len));
	if (!newline)
		return (NULL);
	for (; line && i < pos - 1; i++)
		newline[i] = line[i];
	for (; line && line[i + 1]; i++)
		newline[i] = line[i + 1];
	newline[i] = 0;
	free(line);
	return (newline);
}