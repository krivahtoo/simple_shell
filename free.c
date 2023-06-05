#include "hsh.h"
#include <stdlib.h>

/**
 * free_array - free a malloced array
 *
 * @arr: NULL terminated array
 */
void free_array(char **arr)
{
	int i = 0;

	if (arr != NULL)
	{
		while (arr[i] != NULL)
			free(arr[i++]);
		free(arr);
	}
}

/**
 * free_buf - free a buffer
 *
 * @buf: buffer to free
 */
void free_buf(buf_t *buf)
{
	free(buf->ptr);
	buf->ptr = NULL;
	buf->len = 0;
}

/**
 * free_ctx - free the context variable
 *
 * @ctx: context varible to free
 */
void free_ctx(context_t *ctx)
{
	free_buf(&ctx->buf);
	free_array(ctx->env);
	free_array(ctx->args);
}
