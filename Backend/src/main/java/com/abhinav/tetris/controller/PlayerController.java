package com.abhinav.tetris.controller;

import com.abhinav.tetris.dto.LoginRequest;
import com.abhinav.tetris.dto.LoginResponse;
import com.abhinav.tetris.dto.RegisterRequest;
import com.abhinav.tetris.service.PlayerService;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(path = "api/v1/player")
public class PlayerController {
    private final PlayerService playerService;

    @Autowired
    public PlayerController(PlayerService playerService) {
        this.playerService = playerService;
    }

    @ResponseStatus(HttpStatus.CREATED)
    @PostMapping(path = "/register")
    public void registerPlayer(@Valid @RequestBody RegisterRequest request){
        playerService.registerPlayer(request);
    }

    @PostMapping(path = "/login")
    public LoginResponse loginPlayer(@Valid @RequestBody LoginRequest request){
        return playerService.loginPlayer(request);
    }
}
