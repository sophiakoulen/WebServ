/* ************************************************************************** */
/*                                                     __ __   __             */
/*    WebServ                                         / // / /__ \            */
/*                By: skoulen, bphilago, znichola    / // /_ __/ /            */
/*                                                  /__  __// __/             */
/*                Created: 2023/06/01 23:16:37        /_/  /____/ lausanne.ch */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <sys/socket.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <iostream>
# include <fstream>
# include <netinet/in.h>
# include <sstream>
# include <string>
# include <vector>
# include <sys/stat.h>
# include "typedefs.hpp"
# include "Data.hpp"

#include "HTTPRequest.hpp"

#define ESC_COLOR_RED		"\033[31m"
#define ESC_COLOR_GREEN		"\033[32m"
#define ESC_COLOR_CYAN		"\033[96m"
#define ESC_COLOR_MAGENTA	"\033[35m"
#define ESC_COLOR_RESET		"\033[0m"

#define COL(col, text) col << text << ESC_COLOR_RESET

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

// Define a macro to check for GCC version 12 or Clang version 9
#if defined(__GNUC__) && ((__GNUC__ > 12) || (__GNUC__ == 12 && __GNUC_MINOR__ >= 0))
    #define COMPILER_VERSION_CHECK_GCC_12_OR_CLANG_9
#elif defined(__clang__) && ((__clang_major__ > 9) || (__clang_major__ == 9 && __clang_minor__ >= 0))
    #define COMPILER_VERSION_CHECK_GCC_12_OR_CLANG_9
#endif

// https://stackoverflow.com/a/68363326
#ifndef COMPILER_VERSION_CHECK_GCC_12_OR_CLANG_9
# define __FILE_NAME__ std::max<const char*>(__FILE__,\
    std::max(strrchr(__FILE__, '\\')+1, strrchr(__FILE__, '/')+1))
#endif

#define PERR(msg) \
	std::cerr << __FILE_NAME__ << ":" << __LINE__ << " " \
	<< COL(ESC_COLOR_RED, "Error: ") << msg << std::endl

#define PERR2(msg, msg2) \
	std::cerr << __FILE_NAME__ << ":" << __LINE__ << " " \
	<< COL(ESC_COLOR_RED, "Error: ") << msg << " : " << msg2 << std::endl

int send_to_socket(const std::string &message, int socket_fd);
int send_file_to_socket(const std::string &filename, int socket_fd);
void trim_outside_whitespace(std::string &line);

#define LINEAR_WHITESPACE " \t\v\f"

namespace utils
{
	std::string&	trim(std::string& s, const char *t = LINEAR_WHITESPACE);
	std::string&	sanitizeline(std::string& s);

	pairHostPort getHostPort(const std::string &str);

	Data constructDefaultServer();

	int toInt(const std::string &s);
	void split_around_first_c(char c, const std::string src, std::string &s1, std::string &s2);
	std::string addrIntToString(u_int32_t addr_int);
	u_int32_t addrStringToInt(const std::string &addr_string);
	pairHostPort fd_to_HostPort(int fd);
	std::string fdToString(int fd);
	std::string ifstreamToString(std::ifstream &stream);
	t_getfile_response getFile(const std::string &path, std::string &body);

	std::string getMethodStr(const HTTPRequest &req);
	bool isValideURL(const std::string &str);

	int	parseHeader(const std::string& line, std::pair<std::string, std::string>& header);

	/* case-insensitive string comparison */
	bool	streq_ci(const std::string& s1, const std::string& s2);

	std::string	getFileExtension(const std::string& file);
}

/* use it variable to itterate */
#define FOREACH_VECTOR(type, thing) \
for(std::vector<type>::const_iterator it =thing.begin(); it != thing.end(); ++it)

/* use it variable to itterate */
#define FOREACH_SET(type, thing) \
for(std::set<type>::const_iterator it =thing.begin(); it != thing.end(); ++it)

/* use it variable to itterate */
#define FOREACH_MAP(type, thing) \
for(std::map<std::string, type>::const_iterator it =thing.begin(); it != thing.end(); ++it)

#endif
