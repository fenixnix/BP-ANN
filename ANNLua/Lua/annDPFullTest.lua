_G['os'] = nil
_G['io'] = nil
json = require 'json'

tool = require 'toolmodule'
gUser = nil 

function init()
    math.randomseed(0)
    ann = _InitNerve(2)
end

function setUser(pUser) 
    gUser = pUser 
end

function str2hex(pVar)  

    local hexstr  
    local charcode  
    local allhexstr = ''

    local bytes = pVar
  
    for i = 1, string.len(bytes) do  
  
        local charcode = tonumber(string.byte(bytes, i, i));  
        local hexstr = string.format("%02X", charcode);  
  
        allhexstr=allhexstr..hexstr  
    end  

    return allhexstr;  
end  

function hex2str(pVar)  
    local allhexstr = ''
    for i = 1, string.len(pVar) - 1, 2 do  
  
        local doublebytestr = string.sub(pVar, i, i+1);  
        local n = tonumber(doublebytestr, 16);  
        allhexstr=allhexstr..string.format("%c", n)
    end  
  
    return allhexstr
end

ann = {}
lambda = 0.05

function _Sigmoid(inputSignal)
    result = 1.0/(1.0+ math.exp(-1*inputSignal))
    return result
end

function _InitNerve(wtCnt)
    local n = {}
    n[0] = 0;
    for i = 1 , wtCnt, 1 do
        n[i] = math.random()
    end
    return n
end

function _InitLayer(nCnt,wtCnt)
    local l = {}
    for i = 1, nCnt, 1 do
        l[i] = _InitNerve(wtCnt)
    end
    return l
end

function _InitAnnBp(layerNum)
    local bpAnn = {}
    for i = 1,#layerNum-1,1 do
        bpAnn[i] = _InitLayer(layerNum[i+1],layerNum[i])
    end
    return bpAnn
end

function _RunNerve(nerv,inputs)
    local s = nerv[0]
    for i = 1,#inputs,1 do
        s = s + inputs[i]*nerv[i]
    end
    return _Sigmoid(s);
end

function _TeachNerve(nerv,inputs,errs)
    local O = _RunNerve(nerv,inputs)
    local E = O*(1.0-O)*errs
    for i = 1,#inputs,1 do
        nerv[i] = nerv[i] + lambda*E*inputs[i]
    end
    nerv[0] = nerv[0]+lambda*E
    return E
end

function _TeachNerveO(nerv,inputs,taget)
    local O = _RunNerve(nerv,inputs)
    return _TeachNerve(nerv,inputs,taget - O)
end

function _RunLayer(inputs)

end

function _TeachLayer(inputs,errs)

end

function _TeachLayerO(inputs,outputs)

end

function _GetBpErrs(bpErrSum)

end

function _RunBpAnn(inputs)

end

function _RunBpGetAllLayerOutputs(inputs)

end

function _LearnBpAnn(inputs, outputs)

end

function _Ask(inputs)
    return _RunNerve(ann,inputs)
end

function _Teach(inputs,outputs)
    _TeachNerveO(ann,inputs,outputs[1])
end

--[[
OriginNode Contract Code
{'input':[1,2,3,4]}
--]]
function getAsk(inputString)
    local str = hex2str(inputString)
    local input = json.decode(str)
    local O = _Ask(input['I'])
    return json.encode({output=O})
end

function teach(inputString)
    local str = hex2str(inputString)
    local IO = json.decode(str)
    local O = _Teach(IO['I'],IO['O'])
    return str.." OK!"
end

function getHelp()
    local curTable = {}
    curTable['MethodSet'] = {}
    curTable['MethodSet']['teach'] = {}
    curTable['MethodSet']['teach']['param'] = '{"I":[0,0],"O":[0]}'
    curTable['MethodSet']['teach']['example'] = 'teach {"I":[1,0],"O":[0]}'
    curTable['MethodSet']['teach']['desc'] = '[1,0]/[0] can set any numeric'

    curTable['MethodGet'] = {}
    curTable['MethodGet']['getHelp'] = {}
    curTable['MethodGet']['getHelp']['param'] = 'null'
    curTable['MethodGet']['getHelp']['example'] = 'getHelp null'
    curTable['MethodGet']['getHelp']['desc'] = 'return ann contract help'
    return json.encode(curTable)
end

--[[
SelfTest Code
--]]
function testTeach(times)
    print('Teach And')
    for i = times , 1, -1 
    do  
        _Teach({0,0},{0})
        _Teach({0,1},{0})
        _Teach({1,0},{0})
        _Teach({1,1},{1})
    end
end

function testAsk()
    print('Results:')
    result = _Ask({0,0})
    print(result)
    result = _Ask({0,1})
    print(result)
    result = _Ask({1,0})
    print(result)
    result = _Ask({1,1})
    print(result)
end

function test()
    print('Hello ANN!')
    init()
    toolmodule.PrintTable(ann)
    testAsk()

    testTeach(1000)
    toolmodule.PrintTable(ann)
    testAsk()
    
    testTeach(1000)
    toolmodule.PrintTable(ann)
    testAsk()
    
    testTeach(1000)
    toolmodule.PrintTable(ann)
    testAsk()
end

test()
