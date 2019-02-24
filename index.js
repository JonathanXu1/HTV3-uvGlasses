const express = require('express')
const path = require('path')
const PORT = process.env.PORT || 5000
var io = require('socket.io')(http);

express()
  .use(express.static(path.join(__dirname, 'public')))
  .set('views', path.join(__dirname, 'views'))
  .set('view engine', 'ejs')
  .get('/', (req, res) => res.render('pages/index'))
  .listen(PORT, () => console.log(`Listening on ${ PORT }`))

io.on('connection', function(socket) {
  console.log('User connected: ' + socket.id);
  //socket.emit('light', light);
  socket.on('disconnect', function(){
    console.log('User disconnected: ' + socket.id);
  });
  socket.on('updateData', function(object){
    data = object;
    console.log("Update: ");
    console.log(data);
    io.sockets.emit('updateData', data);
  });
  socket.on("getData", function(){
    io.sockets.emit('updateData', data);
  });
});
