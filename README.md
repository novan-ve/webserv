# Webserv

![CI](https://github.com/novan-ve/webserv/workflows/CI/badge.svg)

Creating a fully functional webserver in C++, based on nginx.
Compliant with RFC 7230-7235.

Supports GET, POST, PUT and HEAD.

## Features
  - Custom configuration files
  - HTTP authentication
  - Compatibility with php-cgi
  - File uploads
  - Parsing of encoded requests
  - Multiple servers running at the same time
  - Crash resistance when handling multiple clients
  - Sigpipe and sigint handling

## Usage
```
make && ./webserv
```
Custom configuration file:
```
make && ./webserv path-to-config-file
```
