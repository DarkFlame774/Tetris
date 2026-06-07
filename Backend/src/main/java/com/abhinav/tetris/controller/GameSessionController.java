package com.abhinav.tetris.controller;

import com.abhinav.tetris.dto.EndGameSessionRequest;
import com.abhinav.tetris.dto.StartGameSessionRequest;
import com.abhinav.tetris.dto.StartGameSessionResponse;
import com.abhinav.tetris.service.GameSessionService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(path = "api/v1/game")
public class GameSessionController {
    private final GameSessionService gameSessionService;

    @Autowired
    public GameSessionController(GameSessionService gameSessionService) {
        this.gameSessionService = gameSessionService;
    }

    @PostMapping(path = "/start")
    public StartGameSessionResponse startGameSession(@RequestBody StartGameSessionRequest request){
        return this.gameSessionService.startGameSession(request);
    }
    @PostMapping(path = "/{sessionId}/end")
    public void endGameSession(@PathVariable Long sessionId, @RequestBody EndGameSessionRequest request){
         this.gameSessionService.endGameSession(sessionId, request);
    }

}
