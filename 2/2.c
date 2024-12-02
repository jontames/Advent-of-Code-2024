#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	int		i;
	int		temp;
	int		minus_check;

	i = 0;
	temp = 0;
	minus_check = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		minus_check = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		temp = (temp * 10) + (nptr[i++] - '0');
	return (temp * minus_check);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		if (i < ft_strlen(s1))
			new_s[i] = s1[i];
		else if (i >= ft_strlen(s1))
			new_s[i] = s2[j++];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*text_update(char *text, char *readen)
{
	char	*temp;

	if (!text || !readen)
		return (NULL);
	temp = ft_strjoin(text, readen);
	free(text);
	return (temp);
}

int	main()
{
	int		fd;
	char	*text = NULL;
	char	*readen;
	int		i;
	int		j;
	int		k;
	int		x;
	char	a[3];
	int		line[9];
	int		check;
	int 	count;
	int 	num;

	fd = open("list.txt", O_RDONLY);

	if (!text)
		text = calloc(1, 1);

	readen = calloc(1, 1001);

	// i = 1;
	while (read(fd, readen, 1000) != 0)
	{
		text = text_update(text, readen);
		i = ft_strlen(readen);
		while (i > 0)
			readen[i--] = '\0';
	}

	i = 0;
	count = 0;
	num = 0;
	while (text[i] != '\0')
	{
		k = 0;
		while (text[i] != '\n' && text[i] != '\0')
		{
			j = 0;
			while (text[i] != ' ' && text[i] != '\n' && text[i] != '\0')
			{
				a[j++] = text[i++];
			}
			a[j] = '\0';
			line[k] = ft_atoi(a);
			k++;
			if (text[i] != '\n')
				i++;
		}
		line[k] = 1000;
		x = 0;
		check = 0;
		while (line[x + 1] != 1000)
		{
			if (line[x] == line[x + 1] - 1 || line[x] == line[x + 1] - 2 || line[x] == line[x + 1] - 3)
				check = 1;
			else if (line[x] == line[x + 2] - 1 || line[x] == line[x + 2] - 2 || line[x] == line[x + 2] - 3)
				check = 1;
			else
			{
				check = 0;
				break;
			}
			x++;
		}
		x = 0;
		if (check != 1)
		{
			while (line[x + 1] != 1000)
			{
				if (line[x] == line[x + 1] + 1 || line[x] == line[x + 1] + 2 || line[x] == line[x + 1] + 3)
					check = 1;
				else if (line[x] == line[x + 2] + 1 || line[x] == line[x + 2] + 2 || line[x] == line[x + 2] + 3)
					check = 1;
				else
				{
					check = 0;
					break;
				}
				x++;
			}
		}
		num++;
/* 		if (check == 1)
			printf("%d ", num); */
		count += check;
		if (text[i] != '\0')
			i++;
	}
	// printf("\n\n");
	printf("%d", count);

	// printf("%s", text);

	free (text);
	free (readen);
}
