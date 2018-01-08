
#include <fcntl.h>
/* 
 * \cmd can be F_GETLK, F_SETLK, F_SETLKW
 * struct flock {
 *     short l_type;  F_RDLCK, F_WRLCK or F_UNLCK 
 *     short l_whence;  SEEK_SET, SEEK_CUR or SEEK_END
 *     off_t l_start;   
 *     off_t l_len;
 *     pid_t l_pid;
 * };
 */
int fcntl(int fd, int cmd, .../* struct flock *flockptr */);

#include <sys/select.h>
/* return non-zero if \fd in \fdset, otherwise return 0 */
int FD_ISSET(int fd, fd_set *fdset);
void FD_CLR(int fd, fd_set *fdset);
void FD_SET(int fd, fd_set *fdset);
void FD_ZERO(fd_set *fdset);

/* return -1 if error
 * return 0 if no-fds are prepared
 * return >0 for the amount of prepared fds*/
int select(int maxfdp1, 
           fd_set *restrict readfds,
           fd_set *restrict writefds,
           fd_set *restrict exceptfds,
           struct timeval *restrict tvptr);

int pselect(int maxfdp1,
            fd_set *restrict readfds,
            fd_set *restrict writefds,
            fd_set *restrict exceptfds,
            const struct timespec *restrict tsptr,
            const sigset_t *restrict sigmask);

#include <poll.h>
/*
 *  struct pollfd {
 *      int fd;
 *      short events;
 *      short revents;
 *  };
 *  POLLIN POLLRDNORM POLLRDBAND POLLPRI
 *  POLLOUT POLLWRNORM POLLWRBAND 
 *  POLLERR POLLHUP POLLNVAL
 */
int poll(struct pollfd fdarray[], nfds_t nfds, int timeout);


#include <sys/epoll.h>

int epoll_create(int size);
int epoll_create1(int flags);

/* 
 * \op can be EPOLL_CTL_ADD EPOLL_CTL_MOD EPOLL_CTL_DEL
 *
 * typedef union epoll_data {
 *     void *ptr;
 *     int  fd;
 *     uint32_t u32;
 *     uint64_t u64;
 * } epoll_data_t;
 *
 * struct epoll_event {
 *     uint32_t events;
 *     epoll_data_t data;
 * };
 * the \events in \epoll_event:
 * EPOLLIN
 * EPOLLOUT
 * EPOLLRDHUP
 * EPOLLPRI
 * EPOLLERR
 * EPOLLHUP
 * EPOLLET  // set the Edge Triggered for \fd
 * EPOLLONESHOT //
 * EPOLLWAKEUP
 *
 * when \epoll_ctl success, reutrns 0. When an error occurs, \epoll_ctl returns -1 and \errno is set
 * EBADF
 * EEXIST
 * EINVAL
 * ENOENT
 * ENOMEM
 * ENOSPC
 * EPERM
 */
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

/*  When successful, \epoll_wait returns the number of fds ready for the requested I/O, or zero if \timeout
 *  When an error occurs, \epoll_wait returns -1 and \errno is set.
 *  \maxevents is the size of \events
 */
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *sigmask);

#include <aio.h>
/*
 * struct aiocb {
 *     int aio_fildes;
 *     off_t aio_offset;
 *     volatile void *aio_buf;
 *     size_t aio_nbytes;
 *     int aio_reqprio;
 *     struct sigevent aio_sigevent;
 *     int aio_lio_opcode;
 * };
 *
 * struct sigevent {
 *     int             sigev_notify;
 *     int             sigev_signo;
 *     union           sigval sigev_value;
 *     void            (*sigev_notify_function)(union sigval);
 *     pthread_attr_t *sigev_notify_attributes;
 * };
 * \sigev_notify can be SIGEV_NONE or SIGEV_SIGNAL or SIGEV_THREAD
 */
