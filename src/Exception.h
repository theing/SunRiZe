/*
 * SunRiZe
 * 
 * (c) 2017 by TheIng ( https://theing.blogspot.com )
 * 
 * This file is part of SunRiZe.
 *
 * SunRiZe is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SunRiZe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _EXCEPTION_H__
#define _EXCEPTION_H__
#include <exception>
#include <error.h>
#include <errno.h>

int strerror_xsi(int errnum, char *buf, size_t buflen);

/**
 * @class Exception
 * @author TheIng
 * @date 06/27/17
 * @file Exception.h
 * @brief The generic dynamic exception.
 * This is a dynamic exception in which the const char * representing the message is passed as constructor parameter.
 */
class Exception : public std::exception
{
  const char *code="";
public:
  /**
   * @brief used internally
   */
  Exception(){}
  /**
   * @brief the real constructor with the message.
   * @param c the message that will be stored as a pointer
   */
  Exception(const char * c):code(c){}; 
  /**
   * @brief the what() of the exception
   * @return the message
   */
  virtual const char* what() const throw() {
    return code;
  }
};

/**
 * @class OSException
 * @author TheIng
 * @date 06/27/17
 * @file Exception.h
 * @brief the OS Exception category.
 * For which exceptions that are raised due to an error raised by the Operating System we can use OSException
 * that read the error string directly from the operating system table, by the errno variabile.
 */

class OSException : public Exception
{
  /// The message is store with a limit of 256 characters.
  char msg[256];
public:
  /**
   * @brief Simple constructor that loads the message too
   */
  OSException() {
    
 #if ((_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && (! _GNU_SOURCE))
    // Using XSI version
    strerror_r(errno,msg,256);
 #else
    // Using GNU (sick brain) Version
    strcpy( msg , strerror_r(errno,msg,256) );
 #endif    
  }
  /**
   * @brief the what() of the exception
   * @return the message
   */
  virtual const char* what() const throw() {
    return msg;
  }
};


#endif // _EXCEPTION_H__