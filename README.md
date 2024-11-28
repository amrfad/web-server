# web-server
Repositori ini berisi hasil pengerjaan tugas besar mata kuliah Sistem Operasi Praktik.  
**Detail tugas besar:** Pembuatan Web Server dari scratch menggunakan bahasa C.

## Progress

### 1. Basic Network Setup
- [x] Create TCP socket
- [x] Bind to port 8080
- [x] Listen for connections
- [x] Accept connections

### 2. Single Client Communication
- [x] Read client request
- [x] Send basic response
- [x] Handle client disconnect
- [x] Basic buffer management

### 3. HTTP Protocol
- [x] Parse request line (GET /path HTTP/1.1)
- [x] Parse request headers
- [x] Parse URL & query params
- [x] Create response with headers
- [x] Handle different HTTP methods
- [x] Set response status codes

### 4. File Handling
- [ ] Serve static files
- [ ] Handle default index.html
- [ ] Set Content-Type
- [ ] Basic directory protection
- [ ] Handle file not found

### 5. Multi-client Support
- [ ] Thread pool
- [ ] Handle multiple connections
- [ ] Connection timeouts
- [ ] Resource cleanup

### 6. Error & Logging
- [ ] Basic error pages (404, 500)
- [ ] Simple access logging
- [ ] Error logging

### Optional Features
- [ ] Keep-alive connections
- [ ] Basic caching
- [ ] Gzip compression
- [ ] Basic authentication
- [ ] Rate limiting

