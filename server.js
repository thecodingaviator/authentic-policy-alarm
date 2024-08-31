const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());

let lastMessageTime = null;

app.post('/customer', (_, res) => {
    lastMessageTime = new Date();
    res.status(200).send();
});

app.get('/beacon', (_, res) => {
    if (lastMessageTime) {
        const currentTime = new Date();
        const timeDiff = (currentTime - lastMessageTime) / 1000;
        if (timeDiff <= 6) {
            return res.send('yes');
        }
    }
    res.send('no');
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});

export default app;
