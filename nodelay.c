/* Copyright 2025 Nubificus Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include <sys/socket.h>
#include <netinet/tcp.h>
#include <stdio.h>

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen) {
    static int (*real_setsockopt)(int, int, int, const void *, socklen_t) = NULL;
    if (!real_setsockopt)
        real_setsockopt = dlsym(RTLD_NEXT, "setsockopt");

    if (level == IPPROTO_TCP && optname == TCP_NODELAY) {
        fprintf(stderr, "[hook] TCP_NODELAY enabled on socket %d\n", sockfd);
    }

    return real_setsockopt(sockfd, level, optname, optval, optlen);
}

int socket(int domain, int type, int protocol) {
    static int (*real_socket)(int, int, int) = NULL;
    if (!real_socket)
        real_socket = dlsym(RTLD_NEXT, "socket");

    int s = real_socket(domain, type, protocol);
    if (domain == AF_INET || domain == AF_INET6) {
        int flag = 1;
        setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));
    }
    return s;
}
