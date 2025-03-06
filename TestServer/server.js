const express = require('express');
const app = express();
const port = 3000;

app.use(express.json()); // JSON-datan käsittely
app.use(express.urlencoded({ extended: true }));
app.use(require('cors')()); // Salli ESP-01 yhteydet

// Reitti, johon ESP-01 voi lähettää dataa
app.post('/data', (req, res) => {
    console.log('Received from ESP-01:', req.body);
    res.send({ message: "Data received!" });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
