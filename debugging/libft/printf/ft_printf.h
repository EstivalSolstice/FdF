/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:47:17 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/14 11:57:08 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <ctype.h>
# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/**
 * @brief   A simplified implementation of printf that handles format specifiers
 *          and prints formatted output to the standard output.
 *
 * @param fmt The format string containing regular characters and specifiers.
 * Additional arguments can be passed based on the format specifiers.
 *
 * @return The number of characters printed, or -1 on error.
 */
int		ft_printf(const char *fmt, ...);

/**
 * @brief 	Processes format specifiers for ft_printf
 * 			and prints the corresponding output.
 *
 * @param fmt   The format specifier.
 * @param args  The list of arguments.
 * @param count Pointer to the total character count.
 *
 * @return 0 on success, -1 on error, or result from ft_handle_specifier.
 */
int		ft_check_inputprintf(const char fmt, va_list args, int *count);

/**
 * @brief   Handles format specifiers for ft_printf.
 *
 * @param fmt   The format specifier to process.
 * @param args  The list of arguments for the specifier.
 * @param count Pointer to the character count being updated.
 *
 * @return 	The number of characters printed for the specifier,
 * 			or -2 if the specifier is invalid.
 */
int		ft_handle_specifier(const char fmt, va_list args, int *count);

/* Function prototypes for each format specifier handler */

/* Handles 'c' (char) conversion */
int		ft_handle_input_c(va_list args, int *count);
/* Handles 's' (string) conversion */
int		ft_handle_input_s(va_list args, int *count);
/* Handles 'p' (pointer) conversion */
int		ft_handle_input_p(va_list args, int *count);
/* Handles 'd' and 'i' (integer) conversions */
int		ft_handle_input_d_i(va_list args, int *count);
/* Handles 'u' (unsigned integer) conversion */
int		ft_handle_input_u(va_list args, int *count);
/* Handles 'x' (hexadecimal,lowercase) conversion */
int		ft_handle_input_x(va_list args, int *count);
/* Handles 'X' (hexadecimal,uppercase) conversion */
int		ft_handle_input_xu(va_list args, int *count);

/**
 * @brief 	Writes a buffer to the specified file descriptor and
 * 			returns the number of bytes written.
 *
 * @param fd 	The file descriptor to write to.
 * @param buf 	The buffer containing the data to write.
 * @param count The number of bytes to write from the buffer.
 *
 * @return The number of bytes written, or -1 on error.
 */
int		ft_write_return_val(int fd, const void *buf, size_t count);

int		ft_pf_strlen(const char *str);
char	*ft_pf_itoa(int n);

#endif