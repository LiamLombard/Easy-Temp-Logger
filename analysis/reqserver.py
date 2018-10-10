import time
from http.server import HTTPServer, BaseHTTPRequestHandler


class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        self.wfile.write(b'Hello, world!')

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        body = self.rfile.read(content_length)
        file = open('data.txt', 'a')
        file.write(str(time.time()) + body.decode("utf-8") + "\n")


httpd = HTTPServer(("0.0.0.0", 8000), SimpleHTTPRequestHandler)
httpd.serve_forever()