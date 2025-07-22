/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:35:29 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/21 11:08:47 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Fungsi untuk mencetak karakter '%' ke layar
int	ft_print_percent(t_format fmt)
{
	(void)fmt; // Abaikan parameter format karena tidak digunakan
	if (write(1, "%", 1) == -1) // Tulis karakter '%' ke layar, jika gagal return -1
		return (-1);
	return (1); // Return jumlah karakter yang dicetak (1)
}

