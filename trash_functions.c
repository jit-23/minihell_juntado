t_cmd *pipe_parse(t_shell *sh)
{
	t_pipe *pp = init_pipe();
	t_pipe *lp;

	lp = NULL;
	printf("sh->rl->head - .%s.\n", sh->rl->head->token);
	if (sh->rl->head && sh->rl->head->type == _PIPE)
		sh->rl->head = sh->rl->head->next;
	printf("(post)sh->rl->head - .%s.\n", sh->rl->head->next->token);
	if (sh->root->type == _EXEC)
	{
		
		//printf("1\n");
		pp->left = sh->root;
		sh->root = (t_cmd *)pp;
		if (peek_future_tokens_type(sh->rl->head, PIPE))
			pipe_parse(sh);
		else
			pp->right = exec_parse(sh, init_exec());
	}
	else if (sh->root->type == _PIPE)
	{
		//printf("2\n");
		lp = last_pipe((t_pipe *)sh->root);
		//printf("2.1\n");
		lp->right = (t_cmd *)pp;
		//printf("2.2\n");
		if (pp->left == NULL)
			//printf("FUCK\n");
		pp->left = exec_parse(sh, init_exec());
//		//printf("rl-> .%s.\n", sh->rl->head->token);
		//printf("2.3\n");
		//printf("2.4\n");
		if (peek_future_tokens_type(sh->rl->head, PIPE))
		{
			//printf("3\n");
			//printf("pipe - rl-> .%s.\n", sh->rl->head->token);
			pipe_parse(sh);
		}
		else
		{
			//printf("4\n");
			////printf("exe - rl-> .%s.\n", sh->rl->head->token);
			////printf("pp - %p\n", &pp);
			// pp->right = (t_cmd *)exec_parse(sh, init_exec()); // pk e que este pp nao functiona? nao existe>?
			//printf("after exec_parse\n");
		}
	}
	return ((t_cmd *)pp);
}