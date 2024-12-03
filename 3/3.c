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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		k = i;
		while ((big[k] == little[j]) && (j < ft_strlen(little)) && (k < len))
		{
			if (j == (ft_strlen(little) - 1))
				return ((char *)&big[k - ft_strlen(little) + 1]);
			k++;
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

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
	char	*temp;
	int		i;
	int		j;
	int		k;
	char	*mul_srch;
	char	a[4];
	char	b[4];
	// int		i_a;
	// int		i_b;
	int		res[1000];
	int		res_count;
	long	final_res;

	fd = open("text.txt", O_RDONLY);

	if (!text)
		text = calloc(1, 1);

	readen = calloc(1, 1001);

	while (read(fd, readen, 1000) != 0)
	{
		text = text_update(text, readen);
		i = ft_strlen(readen);
		while (i > 0)
			readen[i--] = '\0';
	}

	// printf("%s", text);

	i = 0;
	k = 0;
	res_count = 0;
	temp = text;
	while (text[i] != '\0')
	{
		mul_srch = ft_strnstr(text, "mul", ft_strlen(text));
		if (mul_srch == NULL)
			break;
		while (mul_srch[i] != ')')
		{
			i += 3;
			if (mul_srch[i] == '(')
				i++;
			else
				break;
			j = 0;
			while (ft_isdigit(mul_srch[i]) && mul_srch[i] != ',')
			{
				a[j++] = mul_srch[i++];
			}
			a[j] = '\0';
			if (mul_srch[i] != ',')
				break;
			i++;
			j = 0;
			while (ft_isdigit(mul_srch[i]) && mul_srch[i] != ')')
			{
				b[j++] = mul_srch[i++];
			}
			b[j] = '\0';
			if (mul_srch[i] != ')')
				break;
			res[res_count] = atoi(a) * atoi(b);
			res_count++;
		}
		k = ft_strlen(text) - ft_strlen(mul_srch);
		text += k + i + 1;
		i = 0;
	}

	i = 0;
	final_res = 0;
	while (i < res_count)
	{
		final_res += res[i];
		i++;
	}
	printf("%ld", final_res);

	free (temp);
	free (readen);
}
