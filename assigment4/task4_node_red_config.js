const ir = msg.payload.ir ?? parseInt(msg.payload);
msg.payload = ir === 1 ? "open" : "close";
return msg;
