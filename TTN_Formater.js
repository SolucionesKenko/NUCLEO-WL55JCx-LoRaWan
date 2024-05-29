function decodeUplink(input) {
    let bytes = input.bytes;
    let decoded = {};
    let output =  {};
    // Define the packet types as an enum
    const packetTypes = {
        0xA001: "TELEMETRY_STATUS_PACKET",
        0xA002: "TELEMETRY_SENSOR_PACKET",
        0xA003: "TELEMETRY_POSITION_PACKET",
        0xB100: "COMMAND_REPLY_PACKET",
        0xC020: "EVENT_LOG_PACKET"
    };
    // Function to read uint16 from bytes
    function readUint16(buffer, offset) {
        return (buffer[offset] << 8) | buffer[offset + 1];
    }
  
    // Function to read uint32 from bytes
    function readUint32(buffer, offset) {
        return (buffer[offset] << 24) | (buffer[offset + 1] << 16) | (buffer[offset + 2] << 8) | buffer[offset + 3];
    }
  
    // Function to read float from bytes
    function readFloat(buffer, offset) {
        let temp = readUint32(buffer, offset);
        return temp / 10.00;
    }
    
    function buildTelemetryData(buff)
    {
      let telemetryPayload = {};
      telemetryPayload.sensors = {
        timestamp: readUint32(buff, 6),
        temperature: readFloat(buff, 10),
        water_pulses: readFloat(buff, 14),
        water_consumption: readFloat(buff, 18),
        pressure: readFloat(buff, 22),
        humidity: readFloat(buff, 26),
        vBatLevel: buff[30],
      };
          
      if (size > 24)
      {
        telemetryPayload.position.latitude = readUint32(buff, 31),
        telemetryPayload.position.longitude = readUint32(buff, 35),
        telemetryPayload.position.altitude = readUint16(buff, 39);
      }
      return 0;
    }
    
    function buildPayloadCustom(buffer)
    {
      // Read common header
      const type = readUint16(buffer, 0);
      const size = readUint16(buffer, 2);
      // let json = {};
      // json.decoded.type = packetTypes[type];
      // json.decoded.payloadSize = size;
      // json.bytes = buffer;
      // switch(type)
      // {
      //   case 0xA001:
      //     payload.decoded.sequence = sequence;
      //     payload.medatada = buildTelemetryData(bytes);
      //     break;
      // }
      //const payloadSensorData = buildTelemetryData(buffer);
      return {
        packetInfo : {
          type: packetTypes[type],
          payloadSize:size,
          raw: buffer
        },
        metadata: 0
      };
    }
  
  
      // let sequence = readUint16(bytes, 4);
      // // Convert type to string enum
      // decoded.type = packetTypes[type] || "UNKNOWN_PACKET_TYPE";
      // decoded.payloadSize = size;
      // decoded.sequence = sequence;
      // let positionData = {};
      // if (size > 24)
      // {
      //   positionData.latitude = readUint32(bytes, 31),
      //   positionData.longitude = readUint32(bytes, 35),
      //   positionData.altitude = readUint16(bytes, 39);
      // }
      const result = buildPayloadCustom(bytes);
    return {
      data: 
        {
          packetInfo: result.packetInfo,
        metadata: {
          timestamp: readUint32(bytes, 6),
          temperature: readFloat(bytes, 10),
          water_pulses: readFloat(bytes, 14),
          water_consumption: readFloat(bytes, 18),
          pressure: readFloat(bytes, 22),
          humidity: readFloat(bytes, 26),
          vBatLevel: bytes[30],
        },
        // position: positionData
      warnings: [],
      errors: []
    }
    };
  }