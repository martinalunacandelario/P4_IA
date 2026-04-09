/**
 * ============================================================================
 * webpagina.h - Página web completa para el sistema de riego inteligente
 * ============================================================================
 * 
 * Este archivo contiene el código HTML/CSS/JS de la interfaz web.
 * Se incluye desde main.cpp y se sirve en la ruta "/" del servidor web.
 * 
 * MEJORA ADICIONAL: Interfaz web completa con:
 * - Diseño responsivo (funciona en móvil, tablet y PC)
 * - Gráficos de humedad en tiempo real con barras de colores
 * - Botones de control manual de riego por zona
 * - Estado en tiempo real con WebSocket (temperatura, humedad, lluvia, estación)
 * - Estadísticas de aprendizaje IA (total riegos, ahorro estimado, eficiencia)
 * - Actualización automática sin refrescar la página
 * 
 * @author Generado con IA para práctica de FreeRTOS
 * @date Marzo 2026
 * ============================================================================
 */

#ifndef WEBPAGINA_H
#define WEBPAGINA_H

// ==================== PÁGINA WEB COMPLETA ====================

const char* PAGINA_WEB = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=yes">
    <title>🌱 Riego Inteligente | IA Adaptativa</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #1e5f3a 0%, #2e8b57 100%);
            min-height: 100vh;
            padding: 20px;
        }
        
        .container {
            max-width: 1200px;
            margin: 0 auto;
        }
        
        /* Tarjetas */
        .card {
            background: white;
            border-radius: 20px;
            padding: 20px;
            margin-bottom: 20px;
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
            transition: transform 0.3s ease;
        }
        
        .card:hover {
            transform: translateY(-5px);
        }
        
        .card-header {
            border-bottom: 3px solid #2e8b57;
            padding-bottom: 10px;
            margin-bottom: 15px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        
        .card-header h2 {
            color: #1e5f3a;
            font-size: 1.4rem;
        }
        
        .card-header .badge {
            background: #2e8b57;
            color: white;
            padding: 5px 12px;
            border-radius: 20px;
            font-size: 0.8rem;
        }
        
        /* Grid de zonas */
        .zonas-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
            gap: 20px;
        }
        
        .zona-card {
            background: #f8f9fa;
            border-radius: 15px;
            padding: 15px;
            border-left: 5px solid #2e8b57;
            transition: all 0.3s ease;
        }
        
        .zona-card.tomate { border-left-color: #ff6b6b; }
        .zona-card.cesped { border-left-color: #4caf50; }
        .zona-card.suculenta { border-left-color: #ffc107; }
        .zona-card.normal { border-left-color: #2196f3; }
        
        .zona-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 15px;
        }
        
        .zona-nombre {
            font-size: 1.2rem;
            font-weight: bold;
        }
        
        .zona-tipo {
            font-size: 0.8rem;
            padding: 3px 8px;
            border-radius: 12px;
            background: #e0e0e0;
        }
        
        .humedad-container {
            margin: 15px 0;
        }
        
        .humedad-label {
            display: flex;
            justify-content: space-between;
            margin-bottom: 5px;
            font-size: 0.9rem;
        }
        
        .humedad-bar-bg {
            background: #e0e0e0;
            border-radius: 10px;
            height: 25px;
            overflow: hidden;
        }
        
        .humedad-bar {
            background: linear-gradient(90deg, #4caf50, #8bc34a);
            height: 100%;
            border-radius: 10px;
            transition: width 0.5s ease;
            display: flex;
            align-items: center;
            justify-content: flex-end;
            padding-right: 8px;
            color: white;
            font-size: 0.8rem;
            font-weight: bold;
        }
        
        .humedad-bar.seco { background: linear-gradient(90deg, #f44336, #ff9800); }
        .humedad-bar.normal { background: linear-gradient(90deg, #ffc107, #ff9800); }
        .humedad-bar.humedo { background: linear-gradient(90deg, #4caf50, #8bc34a); }
        
        .info-zona {
            display: flex;
            justify-content: space-between;
            margin: 10px 0;
            font-size: 0.85rem;
            color: #666;
        }
        
        .btn-regar {
            background: #2196f3;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 25px;
            cursor: pointer;
            font-size: 0.9rem;
            width: 100%;
            margin-top: 10px;
            transition: all 0.3s ease;
        }
        
        .btn-regar:hover {
            background: #0b7dda;
            transform: scale(1.02);
        }
        
        .btn-regar:active {
            transform: scale(0.98);
        }
        
        /* Estadísticas */
        .stats-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
        }
        
        .stat-card {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 15px;
            border-radius: 15px;
            text-align: center;
        }
        
        .stat-value {
            font-size: 1.8rem;
            font-weight: bold;
        }
        
        .stat-label {
            font-size: 0.8rem;
            opacity: 0.9;
        }
        
        /* Estado del sistema */
        .system-status {
            display: flex;
            flex-wrap: wrap;
            gap: 10px;
            margin-top: 10px;
        }
        
        .status-item {
            background: #f0f0f0;
            padding: 8px 15px;
            border-radius: 20px;
            font-size: 0.85rem;
        }
        
        /* Footer */
        .footer {
            text-align: center;
            margin-top: 20px;
            color: rgba(255,255,255,0.8);
            font-size: 0.8rem;
        }
        
        /* Responsive */
        @media (max-width: 768px) {
            body { padding: 10px; }
            .card { padding: 15px; }
            .zonas-grid { grid-template-columns: 1fr; }
        }
        
        /* Animación de carga */
        .loading {
            display: inline-block;
            width: 20px;
            height: 20px;
            border: 3px solid #f3f3f3;
            border-top: 3px solid #2e8b57;
            border-radius: 50%;
            animation: spin 1s linear infinite;
        }
        
        @keyframes spin {
            0% { transform: rotate(0deg); }
            100% { transform: rotate(360deg); }
        }
        
        /* Alertas */
        .alert {
            padding: 12px;
            border-radius: 10px;
            margin-bottom: 15px;
            display: none;
        }
        
        .alert.success {
            background: #c8e6c9;
            color: #2e7d32;
            display: block;
        }
        
        .alert.error {
            background: #ffcdd2;
            color: #c62828;
            display: block;
        }
    </style>
</head>
<body>
    <div class="container">
        <!-- Cabecera -->
        <div class="card">
            <div class="card-header">
                <h2>🌱 Sistema de Riego Inteligente</h2>
                <span class="badge" id="iaBadge">🤖 IA Adaptativa</span>
            </div>
            <div class="system-status">
                <div class="status-item" id="wifiStatus">📡 WiFi: Conectado</div>
                <div class="status-item" id="internetStatus">🌐 Internet: --</div>
                <div class="status-item" id="clientesStatus">📱 Clientes: --</div>
                <div class="status-item" id="uptimeStatus">⏱️ Uptime: --</div>
            </div>
        </div>
        
        <!-- Alertas -->
        <div id="alert" class="alert"></div>
        
        <!-- Estado en tiempo real -->
        <div class="card">
            <div class="card-header">
                <h2>📊 Estado en Tiempo Real</h2>
                <span class="badge" id="lastUpdate">Actualizando...</span>
            </div>
            <div style="display: flex; flex-wrap: wrap; gap: 20px; justify-content: space-between;">
                <div>
                    <p>🌡️ <strong>Temperatura:</strong> <span id="temp">--</span> °C</p>
                    <p>💧 <strong>Humedad ambiente:</strong> <span id="humedadAmbiente">--</span> %</p>
                </div>
                <div>
                    <p>☔ <strong>Lluvia:</strong> <span id="lluvia">--</span></p>
                    <p>📅 <strong>Estación:</strong> <span id="estacion">--</span></p>
                </div>
                <div>
                    <p>⏰ <strong>Factor hora:</strong> <span id="factorHora">--</span></p>
                    <p>🤖 <strong>Factor IA:</strong> <span id="factorIA">--</span></p>
                </div>
            </div>
        </div>
        
        <!-- Zonas de riego -->
        <div class="card">
            <div class="card-header">
                <h2>💧 Zonas de Riego</h2>
                <span class="badge">4 zonas configuradas</span>
            </div>
            <div class="zonas-grid" id="zonasContainer">
                <div class="loading" style="margin: 20px auto;"></div>
            </div>
        </div>
        
        <!-- Estadísticas IA -->
        <div class="card">
            <div class="card-header">
                <h2>📈 Estadísticas de Aprendizaje IA</h2>
                <span class="badge">Datos en tiempo real</span>
            </div>
            <div class="stats-grid" id="statsContainer">
                <div class="stat-card">
                    <div class="stat-value" id="totalRiegos">0</div>
                    <div class="stat-label">Total de riegos</div>
                </div>
                <div class="stat-card">
                    <div class="stat-value" id="ahorroEstimado">0%</div>
                    <div class="stat-label">Ahorro estimado</div>
                </div>
                <div class="stat-card">
                    <div class="stat-value" id="eficienciaPromedio">0</div>
                    <div class="stat-label">Eficiencia (%/min)</div>
                </div>
                <div class="stat-card">
                    <div class="stat-value" id="aguaAhorrada">0</div>
                    <div class="stat-label">Agua ahorrada (L)</div>
                </div>
            </div>
        </div>
        
        <!-- Control manual -->
        <div class="card">
            <div class="card-header">
                <h2>🎮 Control Manual</h2>
                <span class="badge">Riego inmediato</span>
            </div>
            <div style="display: flex; gap: 10px; flex-wrap: wrap;" id="controlesManuales">
                <button class="btn-regar" style="background: #ff6b6b; width: auto;" onclick="regarManual(0, 60)">🍅 Zona 1 - 1 min</button>
                <button class="btn-regar" style="background: #ff6b6b; width: auto;" onclick="regarManual(0, 300)">🍅 Zona 1 - 5 min</button>
                <button class="btn-regar" style="background: #4caf50; width: auto;" onclick="regarManual(1, 60)">🌿 Zona 2 - 1 min</button>
                <button class="btn-regar" style="background: #ffc107; width: auto;" onclick="regarManual(2, 30)">🌵 Zona 3 - 30s</button>
                <button class="btn-regar" style="background: #2196f3; width: auto;" onclick="regarManual(3, 120)">🌽 Zona 4 - 2 min</button>
            </div>
        </div>
        
        <div class="footer">
            <p>🌱 Sistema de Riego Inteligente v4.0 | IA Adaptativa | FreeRTOS</p>
            <p>Actualización en tiempo real vía WebSocket | Datos persistentes en NVS</p>
        </div>
    </div>
    
    <script>
        // ==================== VARIABLES GLOBALES ====================
        let ws;
        let reconnectInterval = 3000;
        
        // ==================== CONEXIÓN WEBSOCKET ====================
        function conectarWebSocket() {
            const host = window.location.hostname;
            ws = new WebSocket('ws://' + host + ':81');
            
            ws.onopen = function() {
                console.log('WebSocket conectado');
                document.getElementById('alert').style.display = 'none';
            };
            
            ws.onmessage = function(event) {
                const data = JSON.parse(event.data);
                actualizarInterfaz(data);
            };
            
            ws.onclose = function() {
                console.log('WebSocket desconectado, reconectando...');
                setTimeout(conectarWebSocket, reconnectInterval);
            };
            
            ws.onerror = function(error) {
                console.log('WebSocket error:', error);
            };
        }
        
        // ==================== ACTUALIZAR INTERFAZ ====================
        function actualizarInterfaz(data) {
            // Actualizar fecha de última actualización
            const ahora = new Date();
            document.getElementById('lastUpdate').innerText = 'Última: ' + 
                ahora.getHours().toString().padStart(2,'0') + ':' +
                ahora.getMinutes().toString().padStart(2,'0') + ':' +
                ahora.getSeconds().toString().padStart(2,'0');
            
            // Estado general
            if (data.temperatura !== undefined) {
                document.getElementById('temp').innerText = data.temperatura.toFixed(1);
            }
            if (data.humedad_ambiente !== undefined) {
                document.getElementById('humedadAmbiente').innerText = data.humedad_ambiente.toFixed(0);
            }
            if (data.lloviendo !== undefined) {
                document.getElementById('lluvia').innerHTML = data.lloviendo ? '🌧️ SÍ' : '☀️ NO';
            }
            if (data.estacion !== undefined) {
                document.getElementById('estacion').innerHTML = data.estacion;
            }
            if (data.factor_hora !== undefined) {
                document.getElementById('factorHora').innerHTML = data.factor_hora.toFixed(2);
            }
            if (data.factor_ia !== undefined) {
                document.getElementById('factorIA').innerHTML = data.factor_ia.toFixed(2);
            }
            
            // Estado del sistema
            if (data.clientes !== undefined) {
                document.getElementById('clientesStatus').innerHTML = '📱 Clientes: ' + data.clientes;
            }
            if (data.uptime !== undefined) {
                document.getElementById('uptimeStatus').innerHTML = '⏱️ Uptime: ' + data.uptime;
            }
            
            // Zonas
            if (data.zonas !== undefined) {
                renderizarZonas(data.zonas);
            }
            
            // Estadísticas IA
            if (data.estadisticas !== undefined) {
                document.getElementById('totalRiegos').innerHTML = data.estadisticas.total_riegos || 0;
                document.getElementById('ahorroEstimado').innerHTML = data.estadisticas.ahorro_estimado || '0%';
                document.getElementById('eficienciaPromedio').innerHTML = (data.estadisticas.eficiencia_promedio || 0).toFixed(1);
                document.getElementById('aguaAhorrada').innerHTML = data.estadisticas.agua_ahorrada || 0;
            }
        }
        
        // ==================== RENDERIZAR ZONAS ====================
        function renderizarZonas(zonas) {
            const container = document.getElementById('zonasContainer');
            let html = '';
            
            const tipos = ['Tomate', 'Césped', 'Suculenta', 'Normal'];
            const clases = ['tomate', 'cesped', 'suculenta', 'normal'];
            const iconos = ['🍅', '🌿', '🌵', '🌽'];
            
            for (let i = 0; i < zonas.length; i++) {
                const z = zonas[i];
                const humedad = z.humedad || 0;
                let estadoClase = 'normal';
                
                if (humedad < 30) {
                    estadoClase = 'seco';
                } else if (humedad < 50) {
                    estadoClase = 'normal';
                } else {
                    estadoClase = 'humedo';
                }
                
                html += `
                    <div class="zona-card ${clases[i]}">
                        <div class="zona-header">
                            <span class="zona-nombre">${iconos[i]} Zona ${i+1}</span>
                            <span class="zona-tipo">${tipos[i]}</span>
                        </div>
                        <div class="humedad-container">
                            <div class="humedad-label">
                                <span>💧 Humedad del suelo</span>
                                <span><strong>${humedad}%</strong></span>
                            </div>
                            <div class="humedad-bar-bg">
                                <div class="humedad-bar ${estadoClase}" style="width: ${humedad}%">
                                    ${humedad}%
                                </div>
                            </div>
                        </div>
                        <div class="info-zona">
                            <span>📊 Factor IA: ${z.factor_ia.toFixed(2)}</span>
                            <span>📈 Eficiencia: ${z.eficiencia.toFixed(1)}%/min</span>
                        </div>
                        <button class="btn-regar" onclick="regarManual(${i}, 60)">
                            🚿 Regar ahora (1 minuto)
                        </button>
                    </div>
                `;
            }
            
            container.innerHTML = html;
        }
        
        // ==================== REGAR MANUAL ====================
        async function regarManual(zona, tiempo) {
            mostrarAlerta('⏳ Enviando orden de riego a Zona ' + (zona+1) + '...', 'info');
            
            try {
                const response = await fetch('/api/regar', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify({ zona: zona, tiempo: tiempo })
                });
                
                const result = await response.json();
                if (result.status === 'ok') {
                    mostrarAlerta('✅ Riego manual activado en Zona ' + (zona+1) + ' por ' + tiempo + ' segundos', 'success');
                } else {
                    mostrarAlerta('❌ Error al activar riego: ' + (result.msg || 'desconocido'), 'error');
                }
            } catch (error) {
                mostrarAlerta('❌ Error de conexión al servidor', 'error');
            }
        }
        
        // ==================== MOSTRAR ALERTA ====================
        function mostrarAlerta(mensaje, tipo) {
            const alertDiv = document.getElementById('alert');
            if (tipo === 'success') {
                alertDiv.className = 'alert success';
            } else if (tipo === 'error') {
                alertDiv.className = 'alert error';
            } else {
                alertDiv.className = 'alert';
                alertDiv.style.display = 'none';
                return;
            }
            alertDiv.innerHTML = mensaje;
            alertDiv.style.display = 'block';
            
            setTimeout(() => {
                alertDiv.style.display = 'none';
            }, 3000);
        }
        
        // ==================== INICIALIZACIÓN ====================
        conectarWebSocket();
        
        // Actualizar estado de WiFi cada 10 segundos vía HTTP
        setInterval(async () => {
            try {
                const response = await fetch('/api/estado');
                const data = await response.json();
                if (data.wifi_status) {
                    document.getElementById('wifiStatus').innerHTML = '📡 WiFi: ' + data.wifi_status;
                }
                if (data.internet !== undefined) {
                    document.getElementById('internetStatus').innerHTML = '🌐 Internet: ' + (data.internet ? 'SÍ' : 'NO');
                }
            } catch(e) {
                console.log('Error fetching status:', e);
            }
        }, 10000);
    </script>
</body>
</html>
)rawliteral";

#endif // WEBPAGINA_H