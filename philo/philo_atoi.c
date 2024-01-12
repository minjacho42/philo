/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ato.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:08:31 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/12 12:40:33 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	has_overflow_ll(long long num, int next_digit)
{
	long long	after_cal;

	after_cal = num * 10 + next_digit;
	if ((after_cal / 10 != num) || (after_cal % 10 != next_digit))
		return (1);
	else
		return (0);
}

static int	has_overflow_int(int num, int next_digit)
{
	int	after_cal;

	after_cal = num * 10 + next_digit;
	if ((after_cal / 10 != num) || (after_cal % 10 != next_digit))
		return (1);
	else
		return (0);
}

int	philo_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || has_overflow_int(num, (str[i] - '0') * sign))
			return (-1);
		num *= 10;
		num += (str[i] - '0') * sign;
		i++;
	}
	return (num);
}

int	philo_atoll(const char *str)
{
	int			i;
	long long	num;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || has_overflow_ll(num, (str[i] - '0') * sign))
			return (-1);
		num *= 10;
		num += (str[i] - '0') * sign;
		i++;
	}
	return (num);
}
