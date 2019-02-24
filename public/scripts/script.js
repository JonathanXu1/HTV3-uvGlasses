var socket = io();
var data = {};

socket.on('updateData',function(object){
   data = object;
   console.log("Update: ", data);
 });
