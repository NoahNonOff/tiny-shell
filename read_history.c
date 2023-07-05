#include "shell.h"

/*------------- proto ---------------*/
char	past_char(FILE *flux, int mode);
char	next_char(FILE *flux, int mode);
int	getidx_past_line(FILE *flux);
int	getidx_next_line(FILE *flux);

/* ================================= */

FILE	*new_flux(char *name, char *mode)
{
	FILE	*flux;
	char	c;

	flux = fopen(name, mode);
	if (!flux)
		return (NULL);
	fseek(flux, 0, SEEK_END);
	c = past_char(flux, 0);
	while (c == '\n')
	{
		past_char(flux, 1);
		c = past_char(flux, 0);
	}
	return (flux);
}

// mode:
// 0 -> don't move the head reader
// 1 -> move the head reader
char	past_char(FILE *flux, int mode)
{
	char	buff[2] = {0};

	if (!ftell(flux))
		return (0);
	if (fseek(flux, -1, SEEK_CUR))
		return (-1);
	fread(buff, sizeof(char), 1, flux);
	if (mode == 1)
	{
		if (fseek(flux, -1, SEEK_CUR))
			return (-1);
	}
	return (buff[0]);
}

char	next_char(FILE *flux, int mode)
{
	char	buff[2] = {0};
	int		rd_bytes;

	rd_bytes = fread(buff, sizeof(char), 1, flux);
	if (rd_bytes < 1)
		return (0);
	if (mode == 1)
	{
		if (fseek(flux, -1, SEEK_CUR))
			return (-1);
	}
	return (buff[0]);
}

int	getidx_past_line(FILE *flux)
{
	char	c;
	int		size;

	size = 0;
	while ((c = past_char(flux, 0)) != '\n' && c > 0)
		past_char(flux, 1);
	if (c != '\n')
		return (0);
	past_char(flux, 1);
	while ((c = past_char(flux, 0)) != '\n' && c > 0)
	{
		size++;
		past_char(flux, 1);
	}
	return (size);
}

int	getidx_next_line(FILE *flux)
{
	char	c;
	int		size;
	long	pos;

	size = 0;
	while ((c = next_char(flux, 0)) != '\n' && c > 0)
		next_char(flux, 1);
	if (c != '\n')
		return (0);
	next_char(flux, 1);
	pos = ftell(flux);
	while ((c = next_char(flux, 0)) != '\n' && c > 0)
	{
		size++;
		next_char(flux, 1);
	}
	fseek(flux, pos, SEEK_SET);
	return (size);
}

// mode:
// 0 = next line
// 1 = past line
char	*line_from_stream(FILE *flux, int mode)
{
	int		i;
	int		size;
	char	*line;

	if (mode)
		size = getidx_past_line(flux);
	else
		size = getidx_next_line(flux);
	if (!size)
		return (NULL);
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	for (i = 0; i < size; i++)
		line[i] = next_char(flux, 0);
	line[i] = 0;
	return (line);
}

char	*read_first_line(FILE *flux)
{
	char	c;
	int		i;
	int		size;
	char	*line;

	size = 0;
	while ((c = past_char(flux, 0)) != '\n' && c > 0)
	{
		size++;
		past_char(flux, 1);
	}
	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	for (i = 0; i < size; i++)
		line[i] = next_char(flux, 0);
	line[i] = 0;
	return (line);
}
