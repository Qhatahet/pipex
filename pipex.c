/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qais <qais@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:27:45 by qhatahet          #+#    #+#             */
/*   Updated: 2025/01/09 17:07:40 by qais             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_from_pipe(char **argv, char **envp, t_data *data)
//child process to redirect the pipe read end to stdin
//redirect the output to the second file (argv[4])
//and execute the second cmd (argv[3])
{
	int	fd;

	close(data->fd[1]);
	fd = open (argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		ft_exit(data->fd[0]);
	if (access(argv[4], W_OK) == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (errno)
		ft_exit(data->fd[0]);
	dup2(data->fd[0], STDIN_FILENO);
	close(data->fd[0]);
	if (errno)
		ft_exit(data->fd[0]);
	ft_execute(fd, argv[3], envp);
	ft_exit(-1);
}

void	write_into_pipe(char **argv, char **envp, t_data *data)
//child process to redirect the content of the first file (argv[1]) into stdin
//redirect the output to the pipe write end 
//and execute the first cmd (argv[2])
{
	int	fd;

	close(data->fd[0]);
	if (access(argv[1], R_OK) == -1)
		ft_exit(data->fd[1]);
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		ft_exit(data->fd[1]);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (errno)
		ft_exit(data->fd[1]);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[1]);
	if (errno)
		ft_exit(-1);
	ft_execute(fd, argv[2], envp);
	ft_exit(-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
		ft_invalid_args(argc);
	if (pipe(data.fd) == -1)
		ft_exit(-1);
	data.id1 = fork();
	if (errno)
		exit_pipe(&data);
	if (data.id1 == 0)
		write_into_pipe(argv, envp, &data);
	if (data.id1 != 0)
	{
		data.id2 = fork();
		if (errno)
			exit_pipe(&data);
		if (data.id2 == 0)
			read_from_pipe(argv, envp, &data);
	}
	close(data.fd[0]);
	close(data.fd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
