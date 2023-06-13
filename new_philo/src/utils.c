#include "../include/philo.h"

static long long	ft_numspec(const char *str, int i, long long nbr, long long sign)
{
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		if ((nbr * sign) > 2147483647 || (nbr * sign) < -2147483648)
			return (ERRNBR);
		i++;
	}
	if (str[i])
		return (ERRNBR);
	return (nbr * sign);
}

long long	get_num(const char *str)
{
	long long		nbr;
	long long		sign;
	size_t			i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	return (ft_numspec(str, i, nbr, sign));
}
