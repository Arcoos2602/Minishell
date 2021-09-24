
#ifndef STRUCT_H

typedef struct s_redi
{
	int				type;
	char			*put;
	struct	s_redi	*next;
} t_redi;

typedef struct s_pipes
{
	int 			builtin;
	char			put[2];
	char			**command;
	int				error;
	int				exe;
	struct	s_redi	*redi;
	struct	s_pipes	*next;
}	t_pipes;


typedef struct	s_parser
{
	struct s_pipes	*pipe;
	struct s_parser *next;
}				t_parser;


typedef struct	s_path
{
	char 		**path;
	char 		**exec_path;
	int			first[1];
	int     	start;
	int			exit;
	int			pipe_out;
	int 		pipe_in;
	int			starting;
	int 		dont;
	int 		exec;
	int			father;
	int			in_fd;
	int			out_fd;
	t_parser	*parser;
  int     exit_status;
}               t_path;



#endif