// addon.cc内の NODE_API_MODULE(addon, InitAll) が呼ばれる
var Wrapper = require('bindings')('addon');

// addon.cc内の CreateObject() が呼ばれる
var obj = new Wrapper()

// wrapper.cc内で登録した getNum()が呼ばれる
console.log(obj.getNum());
