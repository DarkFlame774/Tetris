package com.abhinav.tetris.controller;

import com.abhinav.tetris.dto.*;
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
    @PostMapping(path = "/end")
    public void endGameSession(@RequestBody EndGameSessionRequest request){
         this.gameSessionService.endGameSession(request);
    }

    @GetMapping(path = "/leaderboard")
    public LeaderboardResponse getLeaderboard(@RequestBody LeaderboardRequest request){
        return this.gameSessionService.getLeaderBoard(request);
    }

}
