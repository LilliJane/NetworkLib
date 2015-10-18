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

#ifndef RINGBUFFER_H_
# define RINGBUFFER_H_

# include <stdlib.h>
# include <string.h>

# define EMPTY	2
# define FULL	1
# define OK	0
# define ERROR	-1

/*
** Ring buffer struct
** Contains:
** - a pointer on the actual buffer in memory
** - a pointer on the buffer end in memory
** - a pointer to the start of valid data
** - a pointer to the end of valid data
** - the number of actual items
*/
typedef struct	s_ringbuffer
{
  char		*buffer;
  unsigned int	start;
  unsigned int	end;
  size_t	count;
  size_t	max;
  size_t	cap;
}		t_ringbuffer;

t_ringbuffer	*init_buffer(size_t max, size_t size);
void		add_item(t_ringbuffer *buffer, char *item);
char		*get_item(t_ringbuffer *buffer, char delim);
void		free_buffer(t_ringbuffer *buf);
int		buffer_status(t_ringbuffer *buf);

#endif /* !RINGBUFFER_H_ */
