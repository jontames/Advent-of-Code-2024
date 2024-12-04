#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	main()
{
	int		fd;
	char	**text = NULL;
	char	readen[20000];
	char	*temp;
	int		xmas_count;
	int		x_position;
	int		i;
	int		j;
	int		k;

	fd = open("text.txt", O_RDONLY);

	if (!text)
		text = calloc(8, 141);

	read(fd, readen, 20000);
	readen[ft_strlen(readen)] = '\0';

	i = 0;
	j = 0;
	while (readen[i] != '\0')
	{
		k = 0;
		text[j] = malloc(141);
		while (readen[i] != '\n' && readen[i] != '\0')
		{
			text[j][k++] = readen[i++];
		}
		text[j][k] = '\0';
		i++;
		j++;
	}
	text[140] = NULL;

	i = 0;
	xmas_count = 0;
	x_position = 0;
	while (text[i] != NULL)
	{
		temp = strchr(text[i], 'X');
		while (*temp != '\0')
		{
			x_position = ft_strlen(text[i]) - ft_strlen(temp);
			j = x_position;
			k = 0;
			while (k < 4 && text[i][j] != '\0')
			{
				if (text[i][j++] == 'X')
					k++;
				else
					break;
				if (text[i][j++] == 'M')
					k++;
				else
					break;
				if (text[i][j++] == 'A')
					k++;
				else
					break;
				if (text[i][j++] == 'S')
				{
					xmas_count++;
					k++;
				}
				else
					break;
			}
			k = 0;
			while (k < 4 && j > 3)
			{
				if (text[i][j--] == 'X')
					k++;
				else
					break;
				if (text[i][j--] == 'M')
					k++;
				else
					break;
				if (text[i][j--] == 'A')
					k++;
				else
					break;
				if (text[i][j--] == 'S')
				{
					xmas_count++;
					k++;
				}
				else
					break;
			}
			temp++;
			temp = strchr(temp, 'X');
			if (temp == NULL)
				break;
		}
		i++;
	}

	printf("%d", xmas_count);

/* 	i = 0;
	while (text[i] != NULL)
	{
		printf("%d: %s\n", i, text[i]);
		i++;
	} */

	// printf("%s", readen);

	i = 0;
	while (text[i] != NULL)
		free (text[i++]);
	free (text);

}
