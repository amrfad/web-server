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
- [ ] Basic buffer management

### 3. HTTP Protocol
- [ ] Parse request line (GET /path HTTP/1.1)
- [ ] Parse request headers
- [ ] Parse URL & query params
- [ ] Create response with headers
- [ ] Handle different HTTP methods
- [ ] Set response status codes

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

