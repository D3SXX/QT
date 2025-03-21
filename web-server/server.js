const express = require('express')
const fs = require('fs')

const app = express()
const port = 10000 // Listening port

app.use(express.json()) // Expect JSON

// Function to get the QML data from the file
function getQMLData(filename) {
  const qmlData = fs.readFileSync(filename, 'utf8')
  return qmlData
}


// Small description of the route (GET)
app.get('/api/v1/getQML', (req, res) => {
  res.send('Api route for getQML') 
})

// POST route
app.post('/api/v1/getQML', (req, res) => {
  const filename = req.body.filename
  const action = req.body.action
  if (action === "close") {
    // stop the web server
    res.send('Closing up the web server')
    process.exit(0)
  }else {
    // get the filename of the QML file and returns the QML data
    const qmlData = getQMLData(filename)
    res.send(qmlData)
  }
})

app.listen(port, () => {
  
})