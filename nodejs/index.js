var xmldom = require('../../myxmldom'); //require('xmldom');


function IXMLReader() {

}


function parse() {

}


IXMLReader.prototype.parse = function parse(source, defaultNSMap, entityMap) {
    var domBuilder = this.domBuilder;

    domBuilder.startDocument();

    _copy(defaultNSMap, defaultNSMap = {});

    parse(source, defaultNSMap, entityMap, domBuilder, this.errorHandler);

    domBuilder.endDocument();
};


function DOMParser(options) {
    this.options = options || {locator: {}};
    this.options.xmlReader = new IXMLReader();
}


DOMParser.prototype = new xmldom.DOMParser();


module.exports = {
    DOMParser: DOMParser
};
