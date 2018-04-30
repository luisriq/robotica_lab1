import { version } from '../../package.json';
import { Router } from 'express';
import facets from './facets';


const SerialPort = require('serialport');
const parsers = SerialPort.parsers;

// Use a `\r\n` as a line terminator
const parser = new parsers.Readline({
  delimiter: '\r\n'
});

const port = new SerialPort('/dev/cu.wchusbserial1420', {
  baudRate: 9600
});

port.pipe(parser);

port.on('open', () => console.log('Port open'));

parser.on('data', console.log);




export default ({ config, db }) => {
	let api = Router();

	// mount the facets resource
	api.use('/servo', facets({ config, db }));

	// perhaps expose some API metadata at the root
	api.get('/', (req, res) => {
		res.json({ version:version });
	});

	api.post('/mover', (req, res) => {
		port.write(req.body.servo+"-"+req.body.grados+"\n")
		res.json({servo: req.body.servo, angulo:req.body.grados });
	});

	return api;
}
