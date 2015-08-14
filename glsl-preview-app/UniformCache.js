var _cache = {};
var _isResetting = false;

function setValue(name, value) {
    if (!_isResetting) {
        _cache[name] = value;
    }
}

function getValue(name) {
    return _cache[name];
}

function reset(newModel) {
    _isResetting = true;
    var count = newModel.rowCount();
    var newCache = {};

    for (var i = 0; i < count; i++) {

        var data = newModel.get(i);
        var dynamicKey = data.name;
        var cacheData = _cache[data.name];

        if (cacheData && cacheData.type === data.type) {
            newCache[data.name] = {value: cacheData.value, type: data.type};
        }
    }

    _cache = newCache;
    _isResetting = false;
}
