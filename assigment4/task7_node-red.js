let distance = msg.payload.data;
msg.payload = {
    "distance": distance,
};

return msg;
