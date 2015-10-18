// The MIT License (MIT)
//
// Copyright (c) 2015 Emeline Gaulard
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "ringbuffer.h"

/*
** Initialization of ring buffer
** the size_t max is about the number of slots to open
** the size_t size is about the size of one slot
*/
t_ringbuffer	*init_buffer(size_t max, size_t size)
{
  t_ringbuffer	*buffer;

  if ((buffer = malloc(sizeof(t_ringbuffer))) == NULL)
    return (NULL);
  if ((buffer->buffer = malloc(sizeof(char) * (max * size))) == NULL)
    return (NULL);
  buffer->max = max;
  buffer->cap = size;
  buffer->count = 0;
  buffer->end = 0;
  buffer->start = 0;
  return (buffer);
}

/*
** Add char* to the actual buffer if there is a slot open
*/
void		add_item(t_ringbuffer *buffer, char *item)
{
  unsigned int	i;
  unsigned int	next;

  if (!buffer)
    return ;
  if (buffer->count >= buffer->max)
    return ;
  for (i = 0; i < strlen(item); ++ i)
    {
      if (item[i] == '\n')
	buffer->count += 1;
      next = (unsigned int)(buffer->start + 1) % (buffer->cap * buffer->max);
      if (next != buffer->end)
	{
	  buffer->buffer[buffer->start] = item[i];
	  buffer->start += 1;
	}
    }
}

/*
** This function returns a char* of characters of the buffer until the delim character
*/
char		*get_item(t_ringbuffer *buf, char delim)
{
  unsigned int	idx;
  unsigned int	size;
  char		*tmp;

  if (buffer_status(buf) == EMPTY)
    return (NULL);
  size = 0;
  for (idx = buf->end; buf->buffer[idx] != delim
	 && idx < buf->max * buf->cap; ++idx)
    size++;
  if (size == buf->max * buf->cap)
    return (NULL);
  if ((tmp = malloc(sizeof(char) * (size + 1))) == NULL)
    return (NULL);
  for (idx = 0; idx < size; ++idx)
    {
      tmp[idx] = buf->buffer[buf->end];
      buf->end = (unsigned int)(buf->end + 1 % (buf->max * buf->cap));
    }
  tmp[idx] = '\0';
  if (buf->buffer[buf->end] == delim)
    buf->end = (unsigned int)(buf->end + 1 % (buf->max * buf->cap));
  buf->count -= 1;
  return (tmp);
}

void		free_buffer(t_ringbuffer *buf)
{
  if (buf->buffer)
    free(buf->buffer);
  free(buf);
}

/*
** Return the actual buffer's status
*/
int		buffer_status(t_ringbuffer *buf)
{
  if (!buf)
    return (ERROR);
  if (buf->count == 0)
    return (EMPTY);
  else if (buf->start + 1 == buf->end)
    return (FULL);
  else
    return (OK);
  return (OK);
}
