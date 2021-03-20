#! /usr/bin/python3
# Unit tester for the webserv project

import unittest
import random
import os
import requests as req

class WebservTestCase(unittest.TestCase):

    def setUp(self):
        """Set class attributes"""
        self.url = 'http://127.0.0.1:8080/'
        self.filename = ''
        for _ in range(10):
            self.filename += chr(random.randint(97, 97 + 25))
        self.filename += '.txt'

    def test_get(self):
        """Simple GET request to /"""
        r = req.get(self.url)
        with open('./html/index.html', 'r') as f:
            contents = f.read().replace('\n', '')
            self.assertEqual(r.text.replace('\r\n', ''), contents)

    def test_get_status_code(self):
        """Test status code of GET request to /"""
        r = req.get(self.url)
        self.assertEqual(r.status_code, 200)

    def test_post(self):
        """Simple POST request to /welcome.php"""
        try:
            f = open('/usr/bin/php-cgi')
        except IOError:
            unittest.skip('No php-cgi found')
        else:
            f.close()
            pload = {'name':'webserv_user','email':'webserv@student.codam.nl'}
            r = req.post(self.url + 'welcome.php',data = pload)
            with open('./test_responses/post.txt', 'r') as f:
                contents = f.read().replace('\n', '')

            self.assertEqual(r.text.replace('\r\n', ''), contents)

    def test_post_status_code(self):
        """Test status code of POST request to /welcome.php"""
        pload = {'name':'webserv_user','email':'webserv@student.codam.nl'}
        r = req.post(self.url + 'welcome.php', data=pload)
        self.assertEqual(r.status_code, 200)

    def test_non_existent(self):
        """Test GET request to non existent resource"""
        r = req.get(self.url + 'nonexistent.html')
        self.assertEqual(r.status_code, 404)

    def test_HEAD(self):
        """Test if response body from HEAD request is empty"""
        r = req.head(self.url)
        self.assertEqual(r.text, '')

    def test_cgi_bash(self):
        """Test GET request to bash script"""
        r = req.get(self.url + 'cgi-bin/date.idk')
        self.assertEqual(r.text[:9], 'Today is:')

    def test_cgi_perl(self):
        """Test GET request to perl script"""
        r = req.get(self.url + 'cgi-bin/perl.cgi')
        contents = ''
        with open('./test_responses/perl.txt', 'r') as f:
            contents = f.read().replace('\n', '')
        self.assertEqual(r.text.replace('\r\n', ''), contents)

    def test_cgi_ruby(self):
        """Test GET request to ruby script"""
        r = req.get(self.url + 'cgi-bin/hello.rb')
        contents = ''
        with open('./test_responses/ruby.txt', 'r') as f:
            contents = f.read().replace('\n', '')
        self.assertEqual(r.text.replace('\r\n', ''), contents)

    def test_php(self):
        """Test GET request to php script"""
        try:
            f = open('/usr/bin/php-cgi')
        except IOError:
            unittest.skip('No php-cgi found')
        else:
            f.close()
            r = req.get(self.url + 'hello.php')
            contents = ''
            with open('./test_responses/php.txt', 'r') as f_obj:
                contents = f_obj.read().replace('\n', '')
            self.assertEqual(r.text.replace('\r\n', ''), contents)

    def test_allow_header(self):
        """Test if 405 response has allow header"""
        r = req.options(self.url)
        self.assertEqual(r.headers['Allow'], 'GET, HEAD, POST')

    def test_content_type_html(self):
        """Test if GET request to html file has correct content-type"""
        r = req.get(self.url)
        self.assertEqual(r.headers['Content-Type'], 'text/html')

    def test_content_type_json(self):
        """Test if GET request to json file has correct content-type"""
        r = req.get(self.url + 'dir/project.json')
        self.assertEqual(r.headers['Content-Type'], 'application/json')
    
    def test_content_length(self):
        """Test if content-length of default error page is correct"""
        r = req.get(self.url + 'nonexistent.html')
        self.assertEqual(r.headers['Content-Length'], '148')
    
    def test_forbidden_method(self):
        """Test forbidden request method"""
        r = req.options(self.url)
        self.assertEqual(r.status_code, 405)

    def test_redirection(self):
        """Test if GET request to directory without / returns redirection status code"""
        r = req.get(self.url + 'dir')
        self.assertEqual(r.url, self.url + 'dir/')

    def test_redirection_status_code(self):
        """Test if GET request to directory without / returns redirection status code"""
        r = req.get(self.url + 'dir', allow_redirects=False)
        self.assertEqual(r.status_code, 301)

    def test_location_header(self):
        """Test if location header is set in 301 response"""
        r = req.get(self.url + 'dir', allow_redirects=False)
        self.assertEqual(r.headers['Location'], self.url + 'dir/')

    def test_1000_get_requests(self):
        """Test if 1000 responses to GET requests arrive correctly"""
        correct = False
        for _ in range(1000):
            r = req.get(self.url)
            with open('./html/index.html', 'r') as f:
                correct = r.text.replace('\r\n', '') == f.read().replace('\n', '')
                if not correct:
                    break
        self.assertTrue(correct)

    def test_put(self):
        """Test if simple PUT request works"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        r = req.put(self.url + 'put_test/' + self.filename, headers=headers, data='0000000000')
        contents = ''
        with open('./html/uploads/' + self.filename, 'r') as f:
            contents = f.read()
        os.system('rm ./html/uploads/' + self.filename)
        self.assertEqual(contents, '0000000000')

    def test_forbidden_put(self):
        """Test PUT request to location where PUT is not allowed"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        r = req.put(self.url, headers=headers)
        self.assertEqual(r.status_code, 405)

    def test_put_existing_file(self):
        """Test if second PUT request to same location returns 204"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        r = req.put(self.url + 'put_test/' + self.filename, headers=headers, data='0000000000')
        contents = ''
        with open('./html/uploads/' + self.filename, 'r') as f:
            contents = f.read()
        r = req.put(self.url + 'put_test/' + self.filename, headers=headers, data='0000000000')
        os.system('rm ./html/uploads/' + self.filename)
        self.assertEqual(r.status_code, 204)

    def test_put_directory(self):
        """Test PUT request to directory"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        r = req.put(self.url + 'put_test/', headers=headers)
        self.assertEqual(r.status_code, 409)

    def test_put_nonexistent_location(self):
        """Test PUT request to file inside non existing directory"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        r = req.put(self.url + 'put_test/nonexistent/new.txt', headers=headers)
        self.assertEqual(r.status_code, 404)

    def test_large_put(self):
        """Test if large PUT request works"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        large_str = ''
        contents = ''
        for _ in range(1000000):
            large_str += chr(random.randint(97, 97 + 25))
        r = req.put(self.url + 'put_test/' + self.filename, headers=headers, data=large_str)
        with open('./html/uploads/' + self.filename, 'r') as f:
            contents = f.read()
        os.system('rm ./html/uploads/' + self.filename)
        self.assertEqual(contents, large_str)
    
    def test_too_large_put(self):
        """Test large PUT request to location with max body size 10"""
        headers = {'Content-Type': 'text/plain', 'Host': '127.0.0.1:8080'}
        r = req.put(self.url + 'put_test_small/' + self.filename, headers=headers, data='000000000000000')
        self.assertEqual(r.status_code, 413)
    
unittest.main()
