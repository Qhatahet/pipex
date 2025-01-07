/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:27:45 by qhatahet          #+#    #+#             */
/*   Updated: 2025/01/07 15:39:37 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_from_pipe(char **argv, char **envp, t_data *data)
{
	int	fd;

	close(data->fd[1]);
	fd = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (access(argv[4], W_OK) == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
	ft_execute(fd, argv[3], envp);
}

void	write_into_pipe(char **argv, char **envp, t_data *data)
{
	int	fd;

	if (access(argv[1], R_OK) == -1)
		exit(EXIT_FAILURE);
	close(data->fd[0]);
	fd = open (argv[1], O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	ft_execute(fd, argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		perror("not enough arguments");
		exit(EXIT_FAILURE);
	}
	if (pipe(data.fd) == -1)
		exit(EXIT_FAILURE);
	data.id1 = fork();
	if (data.id1 == 0)
		write_into_pipe(argv, envp, &data);
	if (data.id1 != 0)
	{
		data.id2 = fork();
		if (data.id2 == 0)
			read_from_pipe(argv, envp, &data);
	}
	close(data.fd[0]);
	close(data.fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
