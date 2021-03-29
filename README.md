# Webserv

![CI](https://github.com/novan-ve/webserv/workflows/CI/badge.svg)

Fully functional webserver from scratch written in C++, based on nginx. Supports GET, POST, PUT and HEAD.

Compliant with the norms for HTTP described in RFC 7230-7235.


## Webserver features
  - HTTP request/response parsing
  - HTTP authentication
  - Custom configuration files
  - Common Gateway Interface (CGI)
  - Php-cgi compatibility
  - File uploads
  - Chunked encoding
  - Multiple server support
  - Signal handling

## Configuration options
  - Port and host of each server
  - Server_names
  - Default error pages
  - Max client body size
  - Allowed HTTP request methods
  - Url root location
  - Directory listing
  - Default file to answer if requested path is a directory
  - CGI

All configuration options are based on the behaviour of nginx.

## Usage
```
make && ./webserv
```
Custom configuration file:
```
make && ./webserv path-to-config-file
```
