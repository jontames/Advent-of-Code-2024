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

void	bubbleSort(int *arr, int n) {
    int 	i;
	int 	j;
	int 	temp;

    for (i = 0; i < n - 1; i++)
	{
        for (j = 0; j < n - i - 1; j++)
		{
            if (arr[j] > arr[j + 1])
			{
                // Intercambiar arr[j] y arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
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
	int		a_list[1000];
	int		b_list[1000];
	char	a[6];
	char	b[6];
	int		res[1000];
	int		suma;
	int		count;
	
	fd = open("list.txt", O_RDONLY);

	if (!text)
		text = calloc(1, 1);

	readen = calloc(1, 701);

	while (read(fd, readen, 700) != 0)
		text = text_update(text, readen);

	i = 0;
	k = 0;
	while (text[i] != '\0')
	{
		j = 0;
		while (text[i] != ' ')
			a[j++] = text[i++];
		a[5] = '\0';
		a_list[k] = ft_atoi(a);
		i += 3;
		j = 0;
		while (text[i] != '\n')
			b[j++] = text[i++];
		b[5] = '\0';
		b_list[k] = ft_atoi(b);
		k++;
		i++;
	}

	bubbleSort(a_list, 1000);
	bubbleSort(b_list, 1000);

	i = 0;
	while (i < 1000)
	{
		j = 0;
		count = 0;
		while (j < 1000)
		{
			if (b_list[j] == a_list[i])
				count++;
			j++;
		}
		res[i] = a_list[i] * count;
		i++;
	}

	i = 0;
	suma = 0;
	while (i < 1000)
	{
		suma += res[i];
		i++;
	}

	i = 0;
	while (i < 1000)
	{
		printf("%d: %d\n", i, a_list[i]);
		i++;
	}
	printf("\n\n\n");

	i = 0;
	while (i < 1000)
	{
		printf("%d: %d\n", i, b_list[i]);
		i++;
	}
	printf("\n\n\n");

	i = 0;
	while (i < 1000)
	{
		printf("%d: %d\n", i, res[i]);
		i++;
	}

	printf("\n\n\n");

	printf("%d\n", suma);
	// printf("%s", text);
	free (text);
	free (readen);
}